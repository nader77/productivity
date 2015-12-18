module App where

import Config
import Date exposing (..)
import Date.Format exposing (format)
import Debug
import Effects exposing (Effects)
import Html exposing (..)
import Html.Attributes exposing (..)
import Http
import Json.Decode exposing ((:=))
import String
import Task
import Utils.Http exposing (getErrorMessageFromHttpResponse)


-- MODEL
type alias Model =
  { host : String
  , status : Status
  , response : Response
  , employee : Employee
  , month : Int
  , year : Int
  }

type Status =
  Init
  | Fetching
  | Fetched
  | HttpError Http.Error

type alias Source = String

type alias Record =
  { id : Int
  , employee : String
  , start : Int
  , end : Maybe Int
  , length : Maybe Int
  , project : Maybe String
  , changeDate : Int
  , source : Source
  }

type alias Response =
  { records : List Record
  , count : Int
  , totalSessionsLength : Int
  }

type alias Employee =
  { id : Int
  , name : String
  }

initialModel : Model
initialModel =
  { host = ""
  , status = Init
  , response =
    { records = []
    , count = 0
    , totalSessionsLength = 0
    }
  , employee =
    { id = 10
    , name = "aya"
    }
  , month = 0
  , year = 0
  }


init : (Model, Effects Action)
init =
  ( initialModel
  , Task.succeed GetData |> Effects.task
  )


-- UPDATE
type Action =
  GetData
  | SetHost String
  | SetLoadTime Int
  | UpdateDataFromServer (Result Http.Error Response)


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


-- VIEW
view : Signal.Address Action -> Model -> Html
view address model =
  let
    totalLength = toString <| roundDecimal 1 <| toFloat model.response.totalSessionsLength / 3600

    roundDecimal decimalPlaces f =
      toFloat (round <| f * 10 ^ decimalPlaces) / 10 ^ decimalPlaces

    row : Record -> Html
    row record =
      let
        timestampFormat : Int -> String -> String
        timestampFormat time format =
          Date.fromTime (toFloat time * 1000) |> Date.Format.format format

        day time = timestampFormat time "%d/%m"

        hour time = timestampFormat time "%H:%M"

        date time = timestampFormat time "%d/%m/%Y %H:%M"

        end =
          case record.end of
            Just end -> hour end
            Nothing -> "-"

        project =
          case record.project of
            Just project ->
              div [ class "ui pink horizontal label" ] [ text project ]

            Nothing ->
              div [] []

        length =
          case record.length of
            Just length -> toString <| roundDecimal 1 <| toFloat length / 3600
            Nothing -> "-"

        changed =
          case record.end of
            Just end ->
              if record.changeDate > end then
                div [ class "edited ui mini label" ]
                  [ span [] [ text "נערך לאחרונה ב- " ]
                  , span [ dir "ltr" ] [ text <| date record.changeDate ]
                  ]
              else
                span [] []

            Nothing ->
              span [] []

        source =
          case record.source of
            "timewatch" ->
              div [ class "ui green horizontal label" ] [ text "שעון נוכחות" ]

            "manual" ->
              div [ class "ui blue horizontal label" ] [ text "דיווח מרחוק" ]

            _ ->
              div [] [ text record.source ]

      in
        tr [ ]
          [ td [] [ text <| day record.start ]
          , td [] [ text <| hour record.start ]
          , td [] [ text end ]
          , td [] [ text length ]
          , td [] [ project ]
          , td [] [ source ]
          , td [] [ changed ]
          ]
  in
    div []
      [ table [ class "ui celled table" ]
        [ thead []
          [ tr []
            [ th [] [ text "תאריך" ]
            , th [] [ text "כניסה" ]
            , th [] [ text "יציאה" ]
            , th [] [ text "שעות" ]
            , th [] [ text "פרויקט" ]
            , th [] [ text "מקור דיווח" ]
            , th [] [ text "הערות" ]
            ]
          ]
        , tbody [] ( List.map row model.response.records )
        , tfoot []
          [ tr []
            [ th [] [ text <| (toString <| List.length model.response.records) ++ " ימים" ]
            , th [ colspan 2 ] []
            , th [] [ text <| totalLength ++ " שעות"]
            , th [ colspan 3 ] []
            ]
          ]
        ]
      ]


-- EFFECTS
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
