add_library(qbt_webui STATIC
    # headers
    api/apicontroller.h
    api/apierror.h
    api/apistatus.h
    api/appcontroller.h
    api/authcontroller.h
    api/clientdatacontroller.h
    api/isessionmanager.h
    api/logcontroller.h
    api/rsscontroller.h
    api/searchcontroller.h
    api/synccontroller.h
    api/torrentcreatorcontroller.h
    api/torrentscontroller.h
    api/transfercontroller.h
    api/serialize/serialize_torrent.h
    clientdatastorage.h
    searchjobmanager.h
    webapplication.h
    websession.h
    webui.h

    # sources
    api/apicontroller.cpp
    api/apierror.cpp
    api/appcontroller.cpp
    api/authcontroller.cpp
    api/clientdatacontroller.cpp
    api/logcontroller.cpp
    api/rsscontroller.cpp
    api/searchcontroller.cpp
    api/synccontroller.cpp
    api/torrentcreatorcontroller.cpp
    api/torrentscontroller.cpp
    api/transfercontroller.cpp
    api/serialize/serialize_torrent.cpp
    clientdatastorage.cpp
    searchjobmanager.cpp
    webapplication.cpp
    websession.cpp
    webui.cpp
)

# embarr-engine serves only the API: the WebUI's own files aren't built in.
if (NOT EMBARR_ENGINE)
    target_sources(qbt_webui INTERFACE www/webui.qrc)
endif()

target_link_libraries(qbt_webui PRIVATE qbt_base)

if (EMBARR_ENGINE)
    target_compile_definitions(qbt_webui PRIVATE EMBARR_ENGINE)
endif()
