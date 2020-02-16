#ifndef __ObModules_H__
#define __ObModules_H__

// Generated by OberonViewer 0.7.5 on 2020-01-27T01:00:45
// Then further developed manually by RK

#include <OberonSystem/Ob_Global.h>

namespace Ob
{
	class Modules : public _Root
	{
	public:
		/* Link and load on RISC; NW 20.10.2013 / 9.4.2016 / RK 25.1.20 */
		static Modules* _inst();
		Modules();
		~Modules();

		// TYPE
		struct ModDesc;

		typedef ModDesc* Module;
        typedef void (*Command)();
		typedef _FxArray<char,32> ModuleName;
		struct ModDesc : public _Root {
			int cmd;
			int code;
			int ent;
			int imp;
			int key;
			ModuleName name;
			Module next;
			int num;
			int ptr;
			int refcnt;
			int size;
		};

		// VAR
		/* addresses */
		Module root;
		int AllocPtr;
		int res;
		ModuleName importing;
		ModuleName imported;

		// PROC
        void Load(_ValArray<char> name, Module& newmod_);
		Command ThisCommand(Module mod, _ValArray<char> name);
		static void Free(_ValArray<char> name);

	};
}

#endif // __ObModules_H__