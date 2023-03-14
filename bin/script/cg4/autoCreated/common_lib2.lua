--全局变量声明
function GlobalDeclare()
    global g_nActionSeq = ::GetVmValue("CurActionSeq");
    global g_szActionID = ::GetConfig("/stInit/nScriptAction."..g_nActionSeq,"","");
    global g_nResponseInterval = 2000;
    global g_szSvrIP = ::GetConfig("/stInitAction/ConnectGamesvrd".."/szSvrIP","","");
    global iSnewrole = 0;
end;
GlobalDeclare();
--检测回包，responseFlag为判断是否收到回包的标识，在指定时间内未收到回包，则跳转到fail_goto_step
function CheckResponse(responseFlag,fail_goto_step,fir_step,sec_step,third_step)
        local nUin = ::GetRobotUin();
        local nFlag, nRet = ::GetRobotValue(nUin, responseFlag);
        if(nFlag == 1) then
            ::LogRun(responseFlag.." success");
			--将本脚本动作执行标识置为1，表示成功
			::SetRobotValue(0, "nCaseStat", 1);
			::EndTrans(responseFlag, 0);
			--重置回包标志
			::SetRobotValue(nUin, responseFlag, 0);
                        ::SetNextStep(fir_step);
         elseif(nFlag == 2) then
                        ::LogFailed(responseFlag.." need to create role!");
                        ::EndTrans(responseFlag, 1);
                        ::SetRobotValue(0, "nCaseStat", 0);
                        ::SetRobotValue(nUin, responseFlag, 0);
                        ::SetNextStep(sec_step);
        elseif(nFlag == 3) then
                        ::LogFailed(responseFlag.." need to delete role!");
                        ::EndTrans(responseFlag, 1);
                        ::SetRobotValue(0, "nCaseStat", 0);
                        ::SetRobotValue(nUin, responseFlag, 0);
                        ::SetNextStep(third_step);
        elseif(nFlag == -1) then
            		::LogFailed(responseFlag.." Failed!");
			--结束事务,如果事务在so中结束，在此则不必重复操作
            		::EndTrans(responseFlag, 0);
			--将本脚本动作执行标识置为0，表示失败
			::SetRobotValue(0, "nCaseStat", 0);
                        --重置回包标志
                        ::SetRobotValue(nUin, responseFlag, 0);
                        ::SetNextStep(fail_goto_step);
        elseif(::Wait(1, g_nResponseInterval) == 1) then
            ::LogFailed(responseFlag.." timeout!");
            ::EndTrans(responseFlag, 0);
			--将本脚本动作执行标识置为0，表示失败
			::SetRobotValue(0, "nCaseStat", 0);
            ::SetNextStep(fail_goto_step);
        else
            ::StayInStep();
        end;
end;
