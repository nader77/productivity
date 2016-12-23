module Pages.MyAccount.View exposing (view)

import Html exposing (a, div, h2, i, p, text, img, Html)
import Html.Attributes exposing (class, href, src)
import RemoteData exposing (RemoteData(..), WebData)
import User.Model exposing (..)


-- VIEW


view : WebData User -> Html a
view user =
    let
        ( name, mail, avatar ) =
            case user of
                Success val ->
                    ( val.name, val.mail, img [ src <| "https://avatars.githubusercontent.com/" ++ val.githubName ] [] )

                _ ->
                    ( "", "", div [] [] )
    in
        div [ class "ui centered card" ]
            [ div [ class "image" ] [ avatar ]
            , div [ class "content" ]
                [ div [ class "header" ] [ text <| "Welcome " ++ name ]
                , div [ class "body" ] [ text <| mail ]
                ]
            ]
