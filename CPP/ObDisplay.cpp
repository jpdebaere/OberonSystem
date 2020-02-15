// Generated by OberonViewer 0.7.5 on 2020-01-27T01:00:45
// Then further developed manually by RK
#include "ObDisplay.h"
#include "QtDisplay.h"
#include <QWidget>
#include <memory>
using namespace Ob;

struct BitStream
{
    quint8 d_byte, d_bit;
    QByteArray d_buf;

    BitStream( const QByteArray& buf ):d_buf(buf),d_byte(0),d_bit(0){}
    bool next()
    {
        quint8 cur = ( d_byte < d_buf.size() ? d_buf[d_byte] : 0 );
        quint8 res = cur & ( 1 << d_bit );
        d_bit++;
        if( d_bit > 7 )
        {
            d_byte++;
            d_bit = 0;
        }
        return res;
    }
    bool eof() const { return d_byte >= d_buf.size(); }
};

static QImage patternToImage( const QByteArray& pat )
{
    Q_ASSERT( pat.size() >= 2 );

    const int w = int(pat[0]);
    const int h = int(pat[1]);
    const int wBytes = ( w + 7 ) / 8;
    const int wSpare = wBytes * 8 - w;

    QImage img( w, h, QImage::Format_Mono );

    BitStream bs(pat.mid(2));
    for( int y = 0; y < h; y++ )
    {
        for( int x = 0; x < w; x++ )
            img.setPixel(x,y, bs.next() );
        for( int i = 0; i < wSpare; i++ )
            bs.next();
    }
    return img.mirrored();
}

static owned_ptr<Display> s_inst;

const int Display::black;
const int Display::white;
const int Display::replace;
const int Display::paint;
const int Display::invert;

Display* Display::_inst()
{
	if( s_inst.get() == 0 )
    {
		s_inst.reset( new Display() );
        s_inst->_init();
    }
	return s_inst.get();
}

static void setPoint( QImage& img, int x, int y, int mode, int color )
{
    if( x < 0 || y < 0 || x >= img.width() || y >= img.height() )
        return;

    if( color > 1 )
        color = 1; // RISK

    const int dst = img.pixelIndex(x,y);
    if( mode == Display::replace )
        img.setPixel(x,y, color );
    else if( mode == Display::paint )
        img.setPixel(x,y, color || dst );
    else if( mode == Display::invert )
        img.setPixel(x,y, ( color || dst ) && !( color && dst ) );
    else
        Q_ASSERT(false);
}

static void setPoint( QImage& img, int x, int y, int mode, int src, int color )
{
    if( x < 0 || y < 0 || x >= img.width() || y >= img.height() )
        return;

    if( color > 1 )
        color = 1; // RISK

    const int dst = img.pixelIndex(x,y);
    if( mode == Display::replace )
        img.setPixel(x,y, src == 0 ? 0 : color );
    else if( mode == Display::paint )
        img.setPixel(x,y, src == 0 ? dst : color );
    else if( mode == Display::invert )
        img.setPixel(x,y, src == 0 ? dst : abs(color - dst) );
    else
        Q_ASSERT(false);
}


/* a pattern is an array of bytes; the first is its width (< 32), the second its height, the rest the raster */
void Display::ReplConst(int color, int x, int y, int w, int h, int mode)
{
    // qDebug() << "ReplConst" << color << x << y << w << h << mode;
    QtDisplay* d = QtDisplay::inst();

    y = QtDisplay::mapToQt(y);

    if( w > 1 && h > 1 )
    {
        for( int i = x; i < x + w; i++ )
        {
            for( int j = y; j > y - h; j-- )
                setPoint( d->d_img, i, j, mode, color );
        }
    }else if( w > 1 )
    {
        for( int i = x; i < x + w; i++ )
            setPoint( d->d_img, i, y, mode, color );
    }else if( h > 1 )
    {
        for( int i = y; i > ( y - h ); i-- )
            setPoint( d->d_img, x, i, mode, color );
    }else
        setPoint( d->d_img, x, y, mode, color );
    d->update();
}

/* PROCEDURE ReplPattern(col, patadr, x, y, w, h, mode: INTEGER); */
/* only for modes = paint, invert */
void Display::CopyPattern(int color, const QByteArray& pattern, int x, int y, int mode)
{
    // qDebug() << "CopyPattern" << color << x << y << mode;
    QtDisplay* d = QtDisplay::inst();

    QImage img = patternToImage(pattern);
    y = QtDisplay::mapToQt(y) - img.height() + 1;

    for( int yi = 0; yi < img.height(); yi++ )
    {
        for( int xi = 0; xi < img.width(); xi++ )
        {
            const int src = img.pixelIndex( xi, yi );
            setPoint( d->d_img, x + xi, y + yi, mode, src, color );
        }
    }
    d->update();
}

/* only for mode = replace */
void Display::CopyBlock(int sx, int sy, int w, int h, int dx, int dy, int mode)
{
    //qDebug() << "CopyBlock" << sx << sy << w << h << dx << dy << mode;
    QtDisplay* d = QtDisplay::inst();

    sy = QtDisplay::mapToQt(sy);
    dy = QtDisplay::mapToQt(dy);
    // qDebug() << "copy block source" << sx << sy << w << h << "dest" << dx << dy;
    QImage img( w, h, QImage::Format_Mono );
    for( int y = 0; y < h; y++ )
    {
        for( int x = 0; x < w; x++ )
            img.setPixel( x, y, d->d_img.pixelIndex( sx + x, sy - h + 1 + y ) );
    }
    //img.save(QString("%1-%2-%3-%4-%5-%6.png").arg(sx).arg(sy).arg(w).arg(h).arg(dx).arg(dy));
    for( int y = 0; y < h; y++ )
    {
        for( int x = 0; x < w; x++ )
            setPoint( d->d_img, dx + x, dy - h + 1 + y, mode, img.pixelIndex( x, y ) );
    }
    d->update();
}

Display::Display()
{
}

void Display::_init()
{
    arrow = QByteArray::fromHex("0F0F 0060 0070 0038 001C 000E 0007 8003 C101 E300 7700 3F00 1F00 3F00 7F00 FF00");
    star = QByteArray::fromHex("0F0F 8000 8220 8410 8808 9004 A002 C001 7F7F C001 A002 9004 8808 8410 8220 8000");
    hook = QByteArray::fromHex("0C0C 070F 8707 C703 E701 F700 7F00 3F00 1F00 0F00 0700 0300 01");
    updown = QByteArray::fromHex("080E 183C 7EFF 1818 1818 1818 FF7E3C18");
    block = QByteArray::fromHex("0808 FFFF C3C3 C3C3 FFFF");

    QtDisplay::inst();

    Width = QtDisplay::Width;
    Height = QtDisplay::Height;
}

Display::~Display()
{
	s_inst.release();
}

