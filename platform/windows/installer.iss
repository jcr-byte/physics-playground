; Inno Setup Script for Physics Playground
; Compile this with Inno Setup Compiler (https://jrsoftware.org/isinfo.php)

#define MyAppName "Physics Playground"
#define MyAppVersion "1.0.0"
#define MyAppPublisher "Physics Playground"
#define MyAppExeName "physics_playground.exe"

[Setup]
; Unique application identifier - do not change after first release
AppId={{e4d47b44-eaf3-4576-93a7-65c4a502309e}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
DefaultDirName={autopf}\{#MyAppName}
DefaultGroupName={#MyAppName}
OutputDir=dist
OutputBaseFilename=PhysicsPlayground-Setup-{#MyAppVersion}
Compression=lzma2
SolidCompression=yes
WizardStyle=modern
; Require 64-bit Windows
ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible
; Application icon
SetupIconFile=assets\icons\icon.ico
UninstallDisplayIcon={app}\physics_playground.exe

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
; Main executable
Source: "build\Release\physics_playground.exe"; DestDir: "{app}"; Flags: ignoreversion

; All required DLLs
Source: "build\Release\*.dll"; DestDir: "{app}"; Flags: ignoreversion

; Runtime assets (window icon, etc.)
Source: "assets\icons\icon.png"; DestDir: "{app}\assets\icons"; Flags: ignoreversion

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\Uninstall {#MyAppName}"; Filename: "{uninstallexe}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
; Option to launch the app after installation
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

