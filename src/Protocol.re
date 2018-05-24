
open Rpc.J;

let pos = (~line, ~character) => o([("line", i(line)), ("character", i(character))]);

let range = (~start, ~end_) => o([("start", start), ("end", end_)]);

open Infix;
let getTextDocument = doc => Json.get("uri", doc) |?> Json.string
    |?> uri => Json.get("version", doc) |?> Json.number
    |?> version => Json.get("text", doc) |?> Json.string
    |?>> text => (uri, version, text);

let getPosition = pos => Json.get("line", pos) |?> Json.number
|?> line => Json.get("character", pos) |?> Json.number
|?>> character => (int_of_float(line), int_of_float(character));

let rgetPosition = pos => (Result.InfixResult.(RJson.get("line", pos) |?> RJson.number
|?> line => RJson.get("character", pos) |?> RJson.number
|?>> character => (int_of_float(line), int_of_float(character))));