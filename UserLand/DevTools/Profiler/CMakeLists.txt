set(SOURCES
        DisassemblyModel.cpp
        main.cpp
        IndividualSampleModel.cpp
        Process.cpp
        Profile.cpp
        ProfileModel.cpp
        SamplesModel.cpp
        TimelineContainer.cpp
        TimelineHeader.cpp
        TimelineTrack.cpp
        TimelineView.cpp
        )

pranaos_app(Profiler ICON app-profiler)
target_link_libraries(Profiler LibGUI LibDesktop LibX86)
