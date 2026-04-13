import pytest
from pathlib import Path

@pytest.fixture
def fixture_log():
    return Path(__file__).parent / "tests" / "fixtures" / "sensor.log"