#ifndef __ObMenuViewers_H__
#define __ObMenuViewers_H__

// Generated by OberonViewer 0.7.5 on 2020-01-27T01:00:45
// Then further developed manually by RK

#include <OberonSystem/Ob_Global.h>
#include <OberonSystem/ObInput.h>
#include <OberonSystem/ObDisplay.h>
#include <OberonSystem/ObViewers.h>
#include <OberonSystem/ObOberon.h>

namespace Ob
{
	class MenuViewers : public _Root
	{
	public:
		/* JG 26.8.90 / 16.9.93 / NW 10.3.2013 */
		static MenuViewers* _inst();
		MenuViewers();
        void _init();
		~MenuViewers();

		// CONST
		static const int extend = 0;
		static const int reduce = 1;
        static const int FrameColor;

		// TYPE
		struct ViewerDesc;
		struct ModifyMsg;

		typedef ViewerDesc* Viewer;
		struct ViewerDesc : public Viewers::ViewerDesc {
			int menuH;
		};
		struct ModifyMsg : public Display::FrameMsg {
			int H;
			int Y;
			int dY;
			int id;
		};

		// PROC
		static void Copy(Viewer V, Viewer& V1);
		static void Draw(Viewers::Viewer V);
		static void Extend(Viewer V, int newY_);
		static void Reduce(Viewer V, int newY_);
		static void Grow(Viewer V, int oldH);
		static void Shrink(Viewer V, int newH_);
		static void Adjust(Display::Frame F, int id, int dY, int Y, int H);
		static void Restore(Viewer V);
		static void Modify(Viewer V, int Y, int H);
		static void Change(Viewer V, int X, int Y, _Set Keys);
		static void Suspend(Viewer V);
		static void Handle(Display::Frame V, Display::FrameMsg& M);
		Viewer New(Display::Frame Menu, Display::Frame Main, int menuH, int X, int Y);

	};
}

#endif // __ObMenuViewers_H__
