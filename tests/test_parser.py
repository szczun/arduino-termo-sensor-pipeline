import pytest
from log_parser.parser import parseLine, openLogFile

@pytest.mark.parametrize("line, expected", [

    ("Mon Apr 13 12:55:22 2026 [INFO] 24.11",    24.11),
    ("Mon Apr 13 12:55:22 2026 [INFO] -5.12",    -5.12),
    ("Mon Apr 13 12:55:22 2026 [INFO]  24.11",   24.11),
    ("Mon Apr 13 12:55:22 2026 [INFO]   24.11",   24.11),

    ("Mon Apr 13 11:55:22 2026 24.11",           None),
    ("Mon Apr 13 11:55:22 2026 24,11",           None),
    ("Mon Apr 13 11:55:22 2026 -5.12",           None),
    ("Mon Apr 13 11:55:22 2026",                 None),

    ("Mon Apr 13 12:55:22 2026 [INFO] 24,11",    None),  
    ("Mon Apr 13 12:55:22 2026 [INFO] 24.11x",   None),
    ("Mon Apr 13 11:55:22 2026 [INFO]",          None),
    
])

def test_parseLine(line, expected):
    assert parseLine(line) == expected

def test_openLogFile(fixture_log):
    res = openLogFile(fixture_log)
    assert len(res) > 0
    assert all(isinstance(v, float) for v in res)
