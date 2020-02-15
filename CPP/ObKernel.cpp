// Generated by OberonViewer 0.7.5 on 2020-01-27T01:00:45
// Then further developed manually by RK
#include "ObKernel.h"
#include <memory>
#include <QtDebug>
using namespace Ob;

static owned_ptr<Kernel> s_inst;

const int Kernel::SectorLength;

Kernel* Kernel::_inst()
{
	if( s_inst.get() == 0 )
		s_inst.reset( new Kernel() );
	return s_inst.get();
}

void Kernel::New(int& ptr, int tag)
{
    qWarning() << "Kernel::New not available";
}

void Kernel::Mark(int pref)
{
    qWarning() << "Kernel::Mark not available";
}

void Kernel::Scan()
{
    qWarning() << "Kernel::Scan not available";
}

void Kernel::GetSector(int src, void* dst)
{
    qWarning() << "Kernel::GetSector not available";
}

int Kernel::Time()
{
    return start.msecsTo(QDateTime::currentDateTime());
}

int Kernel::Clock()
{
    return clock;
}

void Kernel::SetClock(int dt)
{
    clock = dt;
}

void Kernel::Install(int Padr, int at)
{
    qWarning() << "Kernel::Install not available";
}

Kernel::Kernel():clock(0)
{
    start = QDateTime::currentDateTime();
}

Kernel::~Kernel()
{
	s_inst.release();
}

