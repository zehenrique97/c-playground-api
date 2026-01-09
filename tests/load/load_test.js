import http from "k6/http";
import { check, sleep } from "k6";

export const options = {
  scenarios: {
    load_test: {
      executor: "ramping-vus",
      stages: [
        { duration: "1m", target: 20 },
        { duration: "3m", target: 20 },
        { duration: "30s", target: 0 },
      ],
    },
  },
  thresholds: {
    http_req_duration: ["p(99) < 50"],
    http_req_failed: ["rate < 0.01"],
  },
};

export default function () {
  const res = http.get("http://localhost:8080/api/v1/users/1");
  check(res, { 200: (r) => r.status == 200 });
  sleep(1);
}
