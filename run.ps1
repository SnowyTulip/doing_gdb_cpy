$proxyPath = "./proxy/proxy_3slot/or_debug_proxy.exe"
$command_proxy = "$proxyPath -c -p"  
Start-Process powershell.exe -ArgumentList "-NoExit", "-Command", "`"$command_proxy`""

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