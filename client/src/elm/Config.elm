module Config exposing (..)

import Config.Model as Config exposing (Model)
import Dict exposing (..)


local : Model
local =
    { backendUrl = "http://elm-productivity.local"
    , githubClientId = "3edf9fa129f2fb4d0fb9"
    , name = "local"
    }


production : Model
production =
    { backendUrl = "http://productivity-server.gizra.com"
    , githubClientId = "9169e930cd825924839a"
    , name = "gh-pages"
    }


configs : Dict String Model
configs =
    Dict.fromList
        [ ( "localhost", local )
        , ( "example", production )
        ]
