module User.Decoder exposing (decodeUser)

import Json.Decode exposing (nullable, string, Decoder)
import Json.Decode.Pipeline exposing (decode, optional, required)
import User.Model exposing (..)
import Utils.Json exposing (decodeInt)


decodeUser : Decoder User
decodeUser =
    decode User
        |> required "id" decodeInt
        |> required "label" string
        |> required "mail" string
        |> optional "github_username" string ""
