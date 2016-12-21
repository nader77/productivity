module App.Model exposing (initialModel, Flags, Msg(..), Model, Page(..))

import Config.Model
import Pages.Login.Model exposing (initialModel, Model)
import RemoteData exposing (RemoteData(..), WebData)
import User.Model exposing (..)


type Page
    = AccessDenied
    | Login
    | MyAccount
    | PageNotFound


type Msg
    = Logout
    | PageLogin Pages.Login.Model.Msg
    | SetActivePage Page


type alias Model =
    { accessToken : String
    , activePage : Page
    , config : RemoteData String Config.Model.Model
    , pageLogin : Pages.Login.Model.Model
    , user : WebData User
    }


type alias Flags =
    { accessToken : String
    , hostname : String
    }


initialModel : Model
initialModel =
    { accessToken = ""
    , activePage = Login
    , config = NotAsked
    , pageLogin = Pages.Login.Model.initialModel
    , user = NotAsked
    }
