import http from "k6/http";
import { check, sleep } from "k6";

export default function () {
  http.get("http://google.com");
}
