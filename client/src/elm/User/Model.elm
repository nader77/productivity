module User.Model exposing (..)


type alias User =
    { id : Int
    , name : String
    , mail : String
    , githubName : String
    }
