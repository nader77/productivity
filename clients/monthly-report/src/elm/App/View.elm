module App.View where

import App.Model exposing (..)
import App.Update exposing (Action)
import Date exposing (..)
import Date.Format exposing (format)
import Html exposing (..)
import Html.Attributes exposing (..)

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
