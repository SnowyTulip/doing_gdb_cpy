param($t = 0, $c = 1)
# t 为 1 使用工具链路径
# c 为 1 开启实时调试，反之关闭
$proxyPath = "./proxy/proxy_3slot/or_debug_proxy.exe"
if ($t -eq 1){
	$proxyPath = "D:/toolchains/toolchain_3slot_320f/bin/or_debug_proxy.exe"
}
else {
	$proxyPath = "./proxy/proxy_3slot/or_debug_proxy.exe"
}
$command_proxy = "$proxyPath" 
if ($c -eq 1){
	$command_proxy = "$proxyPath -c -p" 
	echo "LiveDebug ON!"
}
else {
	$command_proxy = "$proxyPath  -p" 
	echo "Live Debug OFF!"
}

Start-Process powershell.exe -ArgumentList "-NoExit", "-Command", "`"$command_proxy`""
# D:\doing_gdb_cpy\proxy\proxy_3slot\or_debug_proxy_tool.exe -r 3333 -c -p
if ($LASTEXITCODE -eq 0) {
    Write-Host "command_proxy successfully started"
} else {
    Write-Host "command_proxy failed to start"
}

$gdbPath = "./gdb"
$command = "$gdbPath -iex ""set auto-load safe-path /""" # 运行启动gdb
							 # 具体的gdb参数写在了.gdbinit文件中
							 # gdb会自动执行该文件的内容
							  # 运行本脚本会自动加载 ".\software_lib_driver\software_lib_driver_core0\Release\software_lib_driver_core0.out"
Invoke-Expression -Command $command