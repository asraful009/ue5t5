# Makefile generated by MakefileGenerator.cs
# *DO NOT EDIT*

UNREALROOTPATH = /storage/Linux_Unreal_Engine_5.4.4
GAMEPROJECTFILE =/storage/work_projects/ue5/UE5T5/UE5T5.uproject

TARGETS = \
	UnrealEditor-Linux-DebugGame  \
	UnrealEditor-Linux-Shipping  \
	UnrealEditor \
	UnrealGame-Linux-DebugGame  \
	UnrealGame-Linux-Shipping  \
	UnrealGame \
	UE5T5-Linux-DebugGame  \
	UE5T5-Linux-Shipping  \
	UE5T5 \
	UE5T5Editor-Linux-DebugGame  \
	UE5T5Editor-Linux-Shipping  \
	UE5T5Editor\
	configure

BUILD = bash "$(UNREALROOTPATH)/Engine/Build/BatchFiles/Linux/Build.sh"
PROJECTBUILD = "$(UNREALROOTPATH)/Engine/Binaries/ThirdParty/DotNet/6.0.302/linux/dotnet" "$(UNREALROOTPATH)/Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.dll"

all: StandardSet

RequiredTools: CrashReportClient-Linux-Shipping CrashReportClientEditor-Linux-Shipping ShaderCompileWorker UnrealLightmass EpicWebHelper-Linux-Shipping

StandardSet: RequiredTools UnrealFrontend UE5T5Editor UnrealInsights

DebugSet: RequiredTools UnrealFrontend-Linux-Debug UE5T5Editor-Linux-Debug


UnrealEditor-Linux-DebugGame:
	 $(BUILD) UnrealEditor Linux DebugGame  $(ARGS)

UnrealEditor-Linux-Shipping:
	 $(BUILD) UnrealEditor Linux Shipping  $(ARGS)

UnrealEditor:
	 $(BUILD) UnrealEditor Linux Development  $(ARGS)

UnrealGame-Linux-DebugGame:
	 $(BUILD) UnrealGame Linux DebugGame  $(ARGS)

UnrealGame-Linux-Shipping:
	 $(BUILD) UnrealGame Linux Shipping  $(ARGS)

UnrealGame:
	 $(BUILD) UnrealGame Linux Development  $(ARGS)

UE5T5-Linux-DebugGame:
	 $(PROJECTBUILD) UE5T5 Linux DebugGame  -project="$(GAMEPROJECTFILE)" $(ARGS)

UE5T5-Linux-Shipping:
	 $(PROJECTBUILD) UE5T5 Linux Shipping  -project="$(GAMEPROJECTFILE)" $(ARGS)

UE5T5:
	 $(PROJECTBUILD) UE5T5 Linux Development  -project="$(GAMEPROJECTFILE)" $(ARGS)

UE5T5Editor-Linux-DebugGame:
	 $(PROJECTBUILD) UE5T5Editor Linux DebugGame  -project="$(GAMEPROJECTFILE)" $(ARGS)

UE5T5Editor-Linux-Shipping:
	 $(PROJECTBUILD) UE5T5Editor Linux Shipping  -project="$(GAMEPROJECTFILE)" $(ARGS)

UE5T5Editor:
	 $(PROJECTBUILD) UE5T5Editor Linux Development  -project="$(GAMEPROJECTFILE)" $(ARGS)

configure:
	xbuild /property:Configuration=Development /verbosity:quiet /nologo "$(UNREALROOTPATH)/Engine/Source/Programs/UnrealBuildTool/UnrealBuildTool.csproj"
	$(PROJECTBUILD) -projectfiles -project="\"$(GAMEPROJECTFILE)\"" -game -engine 

.PHONY: $(TARGETS)
