require "../testscript/common_lib.lua"
require "./common_lib2.lua"

function Step1()
	local nUin = ::GetRobotUin();
	g_szActionID = "DisconnectClientNotify";
	::ResetTimer(1);
	::LogRun(g_szActionID.." begin");
	::StartTrans(g_szActionID);
	::DoCommand(g_szActionID, "");
end;

function Step2()
	g_szActionID = "DisconnectClientNotify";
	CheckResponse(g_szActionID, 100, 100);
end;
