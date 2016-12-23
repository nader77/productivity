module Pages.Login.View exposing (view)

import Html exposing (..)
import Html.Attributes exposing (..)
import Html.Events exposing (onClick, onInput, onSubmit)
import Pages.Login.Model exposing (..)
import RemoteData exposing (RemoteData(..), WebData)
import User.Model exposing (..)
import Utils.WebData exposing (viewError)


view : WebData User -> Model -> Html Msg
view user model =
    let
        spinner =
            i [ class "notched circle loading icon" ] []

        ( isLoading, isError ) =
            case user of
                Loading ->
                    ( True, False )

                Failure _ ->
                    ( False, True )

                _ ->
                    ( False, False )

        inputClasses =
            classList
                [ ( "ui action input", True )
                , ( "error", isError )
                ]

        isFetchStatus =
            model.status == Pages.Login.Model.Fetching || model.status == Pages.Login.Model.Fetched

        githubUrl =
            "https://github.com/login/oauth/authorize?client_id=3edf9fa129f2fb4d0fb9&scope=user:email"

        githubLogin =
            div [ class "ui black button" ]
                [ a [ href githubUrl ]
                    [ i [ class "github icon" ] []
                    , span [] [ text "Login with GitHub" ]
                    ]
                ]

        error =
            case user of
                Failure err ->
                    div [ class "ui error" ] [ viewError err ]

                _ ->
                    div [] []
    in
        Html.form
            [ onSubmit TryLogin
            , action "javascript:void(0);"
            , class "ui stacked segment"
            ]
            [ h2 [] [ text "Please login" ]
              -- UserName
            , githubLogin
            , div [ style [ ( "margin-bottom", "20px" ), ( "margin-top", "20px" ) ] ]
                [ text "OR" ]
            , div [ inputClasses ]
                [ input
                    [ type_ "text"
                    , placeholder "Name"
                    , onInput SetName
                    , value model.loginForm.name
                    ]
                    []
                , input
                    [ type_ "password"
                    , placeholder "Password"
                    , onInput SetPassword
                    , value model.loginForm.pass
                    ]
                    []
                  -- Submit button
                , button
                    [ disabled isLoading
                    , class "ui primary button"
                    ]
                    [ span [ hidden <| not isLoading ] [ spinner ]
                    , span [ hidden isLoading ] [ text "Login" ]
                    ]
                ]
            , error
            ]
