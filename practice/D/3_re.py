from typing import List, Tuple
import re


def split_email(email: str) -> Tuple[str]:
    match = re.match(r"(\w+)@([\w.]+)", email)
    if match:
        username = match.group(1)
        domain = match.group(2)
        domain_name, domain_zone = domain.split(".")
        return (username, domain_name, domain_zone)
    raise ValueError('Некорректный email: "' + email + '"')


def split_emails(emails: List[str]) -> List[Tuple[str]]:
    return [split_email(email) for email in emails]


def test_split_emails():
    try:
        emails = [
            "zuck26@facebook.com",
            "page33@google.com",
            "jeff42@amazon.com",
        ]
        result = [
            ("zuck26", "facebook", "com"),
            ("page33", "google", "com"),
            ("jeff42", "amazon", "com"),
        ]
        response = split_emails(emails)
        assert response == result
    except AssertionError:
        print("TEST ERROR")
        traceback.print_exc()
    except Exception as err:
        print("ERROR:", err)
    else:
        print("TEST PASSED")


test_split_emails()
