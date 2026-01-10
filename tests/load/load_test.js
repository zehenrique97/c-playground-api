import http from "k6/http";
import { check, sleep } from "k6";

export const options = {
  scenarios: {
    load_test: {
      executor: "constant-arrival-rate",
      rate: 1000,
      duration: "5m",
      preAllocatedVUs: 500,
      maxVUs: 3000,
    },
  },
  thresholds: {
    http_req_duration: ["p(99) < 20"],
    http_req_failed: ["rate < 0.01"],
  },
};

export default function () {
  const res = http.get("http://localhost:8080/api/v1/users/1");

  check(res, { "Status 200": (r) => r.status == 200 });
}
