module Config.Model exposing (..)


type alias BackendUrl =
    String


type alias Model =
    { backendUrl : BackendUrl
    , githubClientId : String
    , name : String
    }
