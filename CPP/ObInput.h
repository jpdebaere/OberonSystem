#ifndef __ObInput_H__
#define __ObInput_H__

// Generated by OberonViewer 0.7.5 on 2020-01-27T01:00:45
// Then further developed manually by RK

#include <OberonSystem/Ob_Global.h>

namespace Ob
{
	class Input : public _Root
	{
	public:
		/* NW 5.10.86 / 15.11.90 Ceres-2; PDR 21.4.12 / NW 15.5.2013 Ceres-4 / RK 25.1.20 */
		static Input* _inst();
		Input();
		~Input();

        typedef void (*MouseHandler)(const _Set& keys, int x, int y);
        typedef void (*CharHandler)(char ch);
        typedef void (*IdleHandler)();

		// PROC
        static void RegisterMouseHandler(MouseHandler h);
        static void RegisterCharHandler(CharHandler h);
        static void RegisterIdleHandler(IdleHandler h);

        int Available();
		static void Read(char& ch);

		static void Mouse(_Set& keys, int& x, int& y);
		static void SetMouseLimits(int w, int h);

	};
}

#endif // __ObInput_H__
