module Utils.Format where

import Date
import Date.Format


{-- Round a number to the given amount of decimal places. --}
roundDecimal : Int -> Float -> Float
roundDecimal decimalPlaces number =
  let
    factor = 10 ^ (toFloat decimalPlaces)
  in
    toFloat (round <| number * factor) / factor


{-- Format a timestamp --}
formatTimestamp : Int -> String -> String
formatTimestamp time format =
  Date.fromTime (toFloat time * 1000) |> Date.Format.format format
