module Config exposing (..)

import Config.Model as Config exposing (Model)
import Dict exposing (..)
import Time exposing (Time)


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
        [ ( "e910941b.ngrok.io", local )
        , ( "productivity.gizra.com", production )
        ]


cacheTtl : Time.Time
cacheTtl =
    (5 * Time.second)
