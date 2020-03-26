#include "XESDockCmd.h"

XESDockCmd::XESDockCmd()
{

}

XESDockCmd::~XESDockCmd()
{

}

PackDockCmd::PackDockCmd( const std::function<void()> & todo, const std::function<void()> & undo )
	:_Todo( todo ), _Undo( undo )
{

}

void PackDockCmd::Todo()
{
	_Todo();
}

void PackDockCmd::Undo()
{
	_Undo();
}
