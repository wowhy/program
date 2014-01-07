@echo off

set mono="C:\Program Files (x86)\Mono-3.2.3\bin\mono.exe"
set mcs="C:\Program Files (x86)\Mono-3.2.3\lib\mono\4.5\mcs.exe"
set options=-r:System.Core.dll -o+

set prj="D:\My Documents\Projects\StudyProject3\regex_replace"
set output="bin\Release\regex_replace.mono.exe"

@cd %prj%

set assembly=Properties\AssemblyInfo.cs
set source=Program.cs REGEX_REPLACE.cs

%mcs% %options% -out:%output% %assembly% %source%
