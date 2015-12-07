module App where

import Config
import Date exposing (..)
import Date.Format exposing (format)
import Debug
import Effects exposing (Effects)
import Html exposing (..)
import Html.Attributes exposing (class)
import Html.Events exposing (onClick)
import Http
import Json.Decode exposing ((:=))
import String
import Task


-- MODEL
type alias Model =
  { path : String
  , status : Status
  , response : Response
  }

type Status =
  Init
  | Fetching
  | Fetched
  | HttpError Http.Error

type alias Record =
  { id : Int
  , employee : String
  , start : Int
  , end : Maybe Int
  , project : Maybe String
  }

type alias Response =
  { records : List Record
  , count : Int
  }

initialModel : Model
initialModel =
  { path = "api/v1.0/work-sessions"
  , status = Init
  , response =
    { records = []
    , count = 0
    }
  }


init : (Model, Effects Action)
init =
  ( initialModel
  , Task.succeed Reload |> Effects.task
  )


-- UPDATE
type Action =
  Reload
  | UpdateDataFromServer (Result Http.Error Response)


update : Action -> Model -> (Model, Effects Action)
update action model =
  case action of
    Reload ->
      let
        url = Config.backendUrl ++ model.path ++ "?sort=start&filter[employee]=10&month=12&year=2015"
      in
        ( { model | status = Fetching }
        , getJson url Config.accessToken
        )

    UpdateDataFromServer response ->
      case response of
        Ok response ->
          ( { model
            | status = Fetched
            , response = response
            }
          , Effects.none
          )

        Err error ->
          let
            message = getErrorMessageFromHttpResponse error
            _ = Debug.log "Error" message
          in
            ( { model | status = HttpError error }
            , Effects.none
            )

-- VIEW
view : Signal.Address Action -> Model -> Html
view address model =
  let
    row : Record -> Html
    row record =
      let
        timestampFormat : Int -> String -> String
        timestampFormat time format =
          Date.fromTime (toFloat time * 1000) |> Date.Format.format format

        day time = timestampFormat time "%d/%m"

        hour time = timestampFormat time "%H:%M"

        end =
          case record.end of
            Just end -> hour end
            Nothing -> "-"

        project =
          case record.project of
            Just project -> project
            Nothing -> "-"

        total =
          case record.end of
            Just end -> toString <| toFloat (end - record.start) / 3600
            Nothing -> "-"

      in
        tr [ ]
          [ td [] [ text <| day record.start ]
          , td [] [ text <| hour record.start ]
          , td [] [ text <| end ]
          , td [] [ text <| project ]
          , td [] [ text <| total ]
          ]
  in
    div []
      [ table [ class "ui celled table" ]
        [ thead []
          [ tr []
            [ th [] [ text "תאריך" ]
            , th [] [ text "כניסה" ]
            , th [] [ text "יציאה" ]
            , th [] [ text "פרויקט" ]
            , th [] [ text "שעות" ]
            ]
          ]
        , tbody [] ( List.map row model.response.records )
        ]
      ]


-- EFFECTS
getJson : String -> String -> Effects Action
getJson url accessToken =
  Http.send Http.defaultSettings
    { verb = "GET"
    , headers = [ ("access-token", accessToken) ]
    , url = url
    , body = Http.empty
    }
    |> Http.fromJson decodeResponse
    |> Task.toResult
    |> Task.map UpdateDataFromServer
    |> Effects.task


decodeResponse : Json.Decode.Decoder Response
decodeResponse =
  Json.Decode.object2 Response
    ( Json.Decode.at ["data"]
    <| Json.Decode.list
    <| Json.Decode.object5 Record
      ("id" := Json.Decode.int)
      ("employee" := Json.Decode.string)
      ("start" := Json.Decode.int)
      (Json.Decode.maybe ("end" := Json.Decode.int))
      (Json.Decode.maybe (Json.Decode.at["project"] <| ("label" := Json.Decode.string)))
    )
  ("count" := Json.Decode.int)



getErrorMessageFromHttpResponse : Http.Error -> String
getErrorMessageFromHttpResponse error =
  case error of
    Http.Timeout ->
      "Connection has timed out"

    Http.BadResponse code message ->
      message

    Http.NetworkError ->
      "A network error has occured"

    Http.UnexpectedPayload message ->
      "Unexpected response: " ++ message
