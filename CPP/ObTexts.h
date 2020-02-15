#ifndef __ObTexts_H__
#define __ObTexts_H__

// Generated by OberonViewer 0.7.5 on 2020-01-27T01:00:45
// Then further developed manually by RK

#include <OberonSystem/Ob_Global.h>
#include <OberonSystem/ObFiles.h>
#include <OberonSystem/ObFonts.h>

namespace Ob
{
	class Texts : public _Root
	{
	public:
		/* JG 21.11.90 / NW 11.7.90 / 24.12.95 / 22.11.10 / 20.3.2017 */
		static Texts* _inst();
		Texts();
        void _init();
		~Texts();

		// CONST
		/* scanner symbol classes */
		/* invalid symbol */
		static const int Inval = 0;
		/* name s (length len) */
		static const int Name = 1;
		/* literal string s (length len) */
		static const int String = 2;
		/* integer i (decimal or hexadecimal) */
		static const int Int = 3;
		/* real number x */
		static const int Real = 4;
		/* special character c */
		static const int Char = 6;
		/*  TextBlock = TextTag "1" offset run {run} "0" len {AsciiCode}.
      run = fnt [name] col voff len.  */
		static const char TAB = 0x9;
		static const char CR = 0x0D;
		static const int maxD = 9;
		static const char TextTag = 0xF1;
		/* op-codes */
		static const int replace = 0;
		static const int insert = 1;
		static const int delete_ = 2;
		static const int unmark = 3;

		// TYPE
		struct PieceDesc;
		struct TextDesc;
		struct Reader;
		struct Scanner;
		struct BufDesc;
		struct Writer;

		typedef PieceDesc* Piece;
		struct PieceDesc : public _Root {
			int col;
			Files::File f;
			Fonts::Font fnt;
			int len;
			Piece next;
			int off;
			Piece prev;
			int voff;
		};
		typedef TextDesc* Text;
        typedef void (*Notifier)(Text T, int op, int beg, int end );
		struct TextDesc : public _Root {
			bool changed;
			int len;
			Notifier notify_;
			int org_;
			Piece pce;
			Piece trailer;
		};
		/* cache */
		/* cache */
		struct Reader : public _Root {
			int col;
			bool eot;
			Fonts::Font fnt;
			int off;
			int org_;
			Piece ref;
			Files::Rider rider;
			int voff;
		};
		struct Scanner : public Reader {
			char c;
			int class_;
			int i;
			int len;
			int line;
			char nextCh;
			_FxArray<char,32> s;
			float x;
			float y;
		};
		typedef BufDesc* Buffer;
		struct BufDesc : public _Root {
			Piece header;
			Piece last;
			int len;
		};
		struct Writer : public _Root {
			Buffer buf;
			int col;
			Fonts::Font fnt;
			Files::Rider rider;
			int voff;
		};

		// VAR
		Files::File TrailerFile;

		// PROC
		Piece Trailer();
		static void Load(Files::Rider& R, Text T);
		static void Open(Text T, _ValArray<char> name);
		static void Store(Files::Rider& W, Text T);
		static void Close(Text T, _ValArray<char> name);
		static void OpenBuf(Buffer B);
		static void FindPiece(Text T, int pos, int& org_, Piece& pce);
		static void SplitPiece(Piece p, int off, Piece& pr);
		static void Save(Text T, int beg, int end, Buffer B);
		static void Copy(Buffer SB, Buffer DB);
		static void Insert(Text T, int pos, Buffer B);
		static void Append(Text T, Buffer B);
		static void Delete(Text T, int beg, int end, Buffer B);
		static void ChangeLooks(Text T, int beg, int end, _Set sel, Fonts::Font fnt, int col, int voff);
		static void Attributes(Text T, int pos, Fonts::Font& fnt, int& col, int& voff);
		static void OpenReader(Reader& R, Text T, int pos);
		static void Read(Reader& R, char& ch);
		int Pos(Reader& R);
		static void OpenScanner(Scanner& S, Text T, int pos);
		float Ten(int n);
		static void Scan(Scanner& S);
		static void OpenWriter(Writer& W);
		static void SetFont(Writer& W, Fonts::Font fnt);
		static void SetColor(Writer& W, int col);
		static void SetOffset(Writer& W, int voff);
		static void Write(Writer& W, char ch);
		static void WriteLn(Writer& W);
		static void WriteString(Writer& W, _ValArray<char> s);
		static void WriteInt(Writer& W, int x, int n);
		static void WriteHex(Writer& W, int x);
		static void WriteReal(Writer& W, float x, int n);
		static void WriteRealFix(Writer& W, float x, int n, int k);
		static void WritePair(Writer& W, char ch, int x);
		static void WriteClock(Writer& W, int d);

	};
}

#endif // __ObTexts_H__
