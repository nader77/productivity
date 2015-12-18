module App.Update where

import App.Model exposing (..)
import Config
import Date exposing (..)
import Date.Format exposing (format)
import Debug
import Effects exposing (Effects)
import Http
import Json.Decode exposing ((:=))
import String
import Task
import Utils.Http exposing (getErrorMessageFromHttpResponse)


type Action =
  GetData
  | SetHost String
  | SetLoadTime Int
  | UpdateDataFromServer (Result Http.Error Response)


init : (Model, Effects Action)
init =
  ( initialModel
  , Task.succeed GetData |> Effects.task
  )
  
update : Action -> Model -> (Model, Effects Action)
update action model =
  case action of
    GetData ->
      let
        sort = "?sort=start"
        employee = "&filter[employee]=" ++ toString model.employee.id
        month = "&month=" ++ toString model.month
        year = "&year=" ++ toString model.year
        url = model.host ++ "/" ++ Config.sessionsPath ++ sort ++ employee ++ month ++ year
      in
        ( { model | status = Fetching }
        , getJson url
        )

    SetHost host ->
      ( { model | host = host }
      , Effects.none
      )


    SetLoadTime loadTimestamp ->
      let
        datePartToInt format =
          case String.toInt <| Date.Format.format format <| Date.fromTime <| toFloat loadTimestamp of
            Ok int -> int
            _ -> 0
      in
        ( { model
          | year = datePartToInt "%Y"
          , month = datePartToInt "%m"
          }
        , Effects.none
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


getJson : String -> Effects Action
getJson url =
  Http.send Http.defaultSettings
    { verb = "GET"
    , headers = []
    , url = url
    , body = Http.empty
    }
    |> Http.fromJson parseRecords
    |> Task.toResult
    |> Task.map UpdateDataFromServer
    |> Effects.task


parseRecords : Json.Decode.Decoder Response
parseRecords =
  Json.Decode.object3 Response
    ( Json.Decode.at ["data"]
    <| Json.Decode.list
    <| Json.Decode.object8 Record
      ("id" := Json.Decode.int)
      ("employee" := Json.Decode.string)
      ("start" := Json.Decode.int)
      (Json.Decode.maybe ("end" := Json.Decode.int))
      (Json.Decode.maybe ("length" := Json.Decode.int))
      (Json.Decode.maybe (Json.Decode.at["project"] <| ("label" := Json.Decode.string)))
      ("change_date" := Json.Decode.int)
      ("source" := Json.Decode.string)
    )
  ("count" := Json.Decode.int)
  ("total_sessions_length" := Json.Decode.int)
