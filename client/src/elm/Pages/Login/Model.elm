module Pages.Login.Model exposing (..)

import Http
import User.Model exposing (User)


type alias AccessToken =
    String


type alias LoginForm =
    { name : String
    , pass : String
    }


type UserMessage
    = None
    | Error String


type Status
    = Init
    | Fetching
    | Fetched
    | HttpError Http.Error


type alias Model =
    { accessToken : AccessToken
    , hasAccessTokenInStorage : Bool
    , loginForm : LoginForm
    , status : Status
    , userMessage : UserMessage
    }


type Msg
    = HandleFetchedAccessToken (Result Http.Error AccessToken)
    | HandleFetchedUser AccessToken (Result Http.Error User)
    | SetName String
    | SetPassword String
    | TryLogin


initialModel : Model
initialModel =
    { accessToken =
        ""
        -- We start by assuming there's already an access token it the localStorage.
        -- While this property is set to True, the login form will not appear.
    , hasAccessTokenInStorage = True
    , loginForm = LoginForm "admin" "admin"
    , status = Init
    , userMessage = None
    }
