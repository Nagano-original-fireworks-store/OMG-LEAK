--[[
    brief：   执行动作，检测回包
--]] 

require "../testscript/common_lib.lua"
require "./common_lib2.lua"
function Step1()
        GlobalDeclare();
        local local_szActionID = "ConnectGamesvrd";
        ::LogRun(local_szActionID.." begin");

        ::SetRobotValue(0, "nCaseStat", 0);
		::SetRobotValue(0, "openid", 0);
        local nUin = ::GetRobotUin();
        if (nUin == 0) then
                ::LogFailed(local_szActionID..": get uin is 0");
                ::Finished();
        else
                local nIsConnect = ::IsRobotConnect(nUin);
                if (nIsConnect == 0) then                               
                        ::StartRobotConnect(nUin, g_szSvrIP);
                end

                local nReConnTime = ::GetRobotValue(0, "nReconnectTimes");
                if (nReConnTime == 0) then
                        ::SetRobotValue(0, "nReconnectTimes", 1);           
                end

        end
end;

function Step2()
        local nUin = ::GetRobotUin();
        local local_szActionID = "ConnectGamesvrd";
        local nIsConnect = ::IsRobotConnect(nUin);
        if (nIsConnect == 2) then                                   
                ::LogRun(local_szActionID.." connect success");
                ::SetRobotValue(0, "nCaseStat", 1);
        elseif (nIsConnect == -2) then                              
                local nReConnTime = ::GetRobotValue(0, "nReconnectTimes");
                if (nReConnTime > 5) then
                        ::LogFailed(local_szActionID.."reconnect failed");
                        Exit(local_szActionID, nUin, "reconnect failed");
                elseif (::Wait(1,3000) == 1) then
                        ::LogFailed(local_szActionID.." reconnect "..nReConnTime);
                        ::RobotDisconnect(nUin);
                        ::SetRobotValue(0, "nReconnectTimes", nReConnTime+1);
                        ::SetNextStep(1);
                else
                        ::StayInStep();
                end
       elseif (::Wait(1,3000) == 1) then
                local nReConnTime = ::GetRobotValue(0, "nReconnectTimes");
                if (nReConnTime > 5) then
                        ::LogFailed(local_szActionID.."reconnect failed");
                        Exit(local_szActionID, nUin, "reconnect failed");
                else
                       ::LogFailed(local_szActionID.." reconnect "..nReConnTime);
                        ::RobotDisconnect(nUin);
                        ::SetRobotValue(0, "nReconnectTimes", nReConnTime+1);
                        ::SetNextStep(1);

               end
        else
                ::StayInStep();
        end
end;


--执行完成
function Step100()
    local nUin = ::GetRobotUin();
    ::Finished();
end;
