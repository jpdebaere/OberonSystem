#ifndef __ObFiles_H__
#define __ObFiles_H__

// Generated by OberonViewer 0.7.5 on 2020-01-27T01:00:45
// Then further developed manually by RK

#include <OberonSystem/Ob_Global.h>

#include <QBuffer>
#include <QFile>

namespace Ob
{
	class Files : public _Root
	{
	public:
		/* NW 11.1.86 / 22.9.93 / 25.5.95 / 25.12.95 / 15.8.2013 / RK 25.1.20 */
		static Files* _inst();
		Files();
		~Files();

		// TYPE
		struct Rider;
		struct FileDesc;

		typedef FileDesc* File;
		struct Rider : public _Root {
			bool eof;
			int res;
            // c++ implementation:
            QBuffer d_buf;
            FileDesc* d_file;
		};
		struct FileDesc : public _Root {

            // c++ implementation:
            QByteArray d_data;
            QByteArray d_name;
		};

		// PROC
        File Old(_ValArray<char> name); // open
        File New(_ValArray<char> name); // create
        void Register(File f); // flush to disk
        void Delete(_ValArray<char> name, int& res);
        void Rename(_ValArray<char> old, _ValArray<char> new_, int& res);
		int Length(File f);
		static void Set(Rider& r, File f, int pos);
		int Pos(Rider& r);
		File Base(Rider& r);
		static void ReadByte(Rider& r, uint8_t& x);
		static void Read(Rider& r, char& ch);
		static void ReadInt(Rider& R, int& x);
		static void ReadString(Rider& R, _VarArray<char> x);
		static void WriteByte(Rider& r, uint8_t x);
		static void Write(Rider& r, char ch);
		static void WriteInt(Rider& R, int x);
		static void WriteString(Rider& R, _ValArray<char> x);
		static void RestoreList();

        // implementation
        void setFileSystemPath( const QString& );

    private:
        QString d_fileSystemPath;
	};
}

#endif // __ObFiles_H__
