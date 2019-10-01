##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=nwthpool
ConfigurationName      :=Debug
WorkspacePath          :=/home/hrishikesh/work/github/cpp_new_std/perf_limits
ProjectPath            :=/home/hrishikesh/work/github/cpp_new_std/perf_limits/nwthpool
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Hrishikesh
Date                   :=01/10/19
CodeLitePath           :=/home/hrishikesh/.codelite
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="nwthpool.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -lboost_system -lpthread -lboost_thread
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)/home/hrishikesh/work/boost/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/home/hrishikesh/work/boost/lib 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -W -std=c++17 -std=c++14 -std=c++11 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/application.cpp$(ObjectSuffix) $(IntermediateDirectory)/ConnectionManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/Server.cpp$(ObjectSuffix) $(IntermediateDirectory)/Connection.cpp$(ObjectSuffix) $(IntermediateDirectory)/pool.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/hrishikesh/work/github/cpp_new_std/perf_limits/nwthpool/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/application.cpp$(ObjectSuffix): application.cpp $(IntermediateDirectory)/application.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/hrishikesh/work/github/cpp_new_std/perf_limits/nwthpool/application.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/application.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/application.cpp$(DependSuffix): application.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/application.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/application.cpp$(DependSuffix) -MM application.cpp

$(IntermediateDirectory)/application.cpp$(PreprocessSuffix): application.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/application.cpp$(PreprocessSuffix) application.cpp

$(IntermediateDirectory)/ConnectionManager.cpp$(ObjectSuffix): ConnectionManager.cpp $(IntermediateDirectory)/ConnectionManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/hrishikesh/work/github/cpp_new_std/perf_limits/nwthpool/ConnectionManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ConnectionManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ConnectionManager.cpp$(DependSuffix): ConnectionManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ConnectionManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ConnectionManager.cpp$(DependSuffix) -MM ConnectionManager.cpp

$(IntermediateDirectory)/ConnectionManager.cpp$(PreprocessSuffix): ConnectionManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ConnectionManager.cpp$(PreprocessSuffix) ConnectionManager.cpp

$(IntermediateDirectory)/Server.cpp$(ObjectSuffix): Server.cpp $(IntermediateDirectory)/Server.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/hrishikesh/work/github/cpp_new_std/perf_limits/nwthpool/Server.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Server.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Server.cpp$(DependSuffix): Server.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Server.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Server.cpp$(DependSuffix) -MM Server.cpp

$(IntermediateDirectory)/Server.cpp$(PreprocessSuffix): Server.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Server.cpp$(PreprocessSuffix) Server.cpp

$(IntermediateDirectory)/Connection.cpp$(ObjectSuffix): Connection.cpp $(IntermediateDirectory)/Connection.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/hrishikesh/work/github/cpp_new_std/perf_limits/nwthpool/Connection.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Connection.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Connection.cpp$(DependSuffix): Connection.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Connection.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Connection.cpp$(DependSuffix) -MM Connection.cpp

$(IntermediateDirectory)/Connection.cpp$(PreprocessSuffix): Connection.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Connection.cpp$(PreprocessSuffix) Connection.cpp

$(IntermediateDirectory)/pool.cpp$(ObjectSuffix): pool.cpp $(IntermediateDirectory)/pool.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/hrishikesh/work/github/cpp_new_std/perf_limits/nwthpool/pool.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/pool.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pool.cpp$(DependSuffix): pool.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pool.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/pool.cpp$(DependSuffix) -MM pool.cpp

$(IntermediateDirectory)/pool.cpp$(PreprocessSuffix): pool.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pool.cpp$(PreprocessSuffix) pool.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


