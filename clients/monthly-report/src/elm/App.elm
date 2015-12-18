module App where

import App.Model exposing (..)
import App.Update exposing (Action)
import App.View
import Effects exposing (Effects)
import Html exposing (..)


init : (Model, Effects Action)
init =
  App.Update.init


-- UPDATE
update : Action -> Model -> (Model, Effects Action)
update action model =
  App.Update.update action model

-- VIEW
view : Signal.Address Action -> Model -> Html
view address model =
  App.View.view address model
