
import Effects exposing (Never)
import App exposing (init, update, view)
import Html
import StartApp
import Task

app : StartApp.App App.Model
app =
  StartApp.start
    { init = init
    , update = update
    , view = view
    , inputs =
      [ Signal.map App.SetHost host
      , Signal.map App.SetLoadTime loadTimestamp
      ]
    }


main : Signal Html.Html
main =
  app.html


port tasks : Signal (Task.Task Never ())
port tasks =
  app.tasks

port host : Signal String
port loadTimestamp : Signal Int
