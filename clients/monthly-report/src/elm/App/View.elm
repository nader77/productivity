module App.View where

import App.Model exposing (..)
import App.Update exposing (Action)
import Html exposing (..)
import Html.Attributes exposing (class, colspan, dir)
import Utils.Format exposing (roundDecimal, formatTimestamp)


view : Signal.Address Action -> Model -> Html
view address model =
  div []
    [ monthlyTable model ]

monthlyTable : Model -> Html
monthlyTable model =
  let
    totalLength = toString <| roundDecimal 1 <| toFloat model.response.totalSessionsLength / 3600
  in
    table [ class "ui celled table monthly-report" ]
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


row : Record -> Html
row record =
  let
    day time = formatTimestamp time "%d/%m"
    hour time = formatTimestamp time "%H:%M"
    date time = formatTimestamp time "%d/%m/%Y %H:%M"

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
