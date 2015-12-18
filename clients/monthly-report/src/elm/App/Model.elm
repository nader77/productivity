module App.Model where

import Http

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
