import importlib.util
import subprocess
import unittest
from unittest.mock import patch

spec = importlib.util.spec_from_file_location("runner", "scripts/run.py")
runner = importlib.util.module_from_spec(spec)
spec.loader.exec_module(runner)


class BootRunnerTests(unittest.TestCase):
    @patch.object(runner.subprocess, "run")
    def test_accepts_successful_boot(self, run):
        run.return_value = subprocess.CompletedProcess([], 33, "Nivo OS: boot OK\nDesktop: Willkommen\n", "")
        self.assertEqual(runner.main(), 0)

    @patch.object(runner.subprocess, "run")
    def test_rejects_missing_desktop(self, run):
        run.return_value = subprocess.CompletedProcess([], 33, "Nivo OS: boot OK", "")
        self.assertEqual(runner.main(), 1)

    @patch.object(runner.subprocess, "run", side_effect=subprocess.TimeoutExpired("qemu", 15))
    def test_timeout_is_failure(self, run):
        self.assertEqual(runner.main(), 1)

    @patch.object(runner.subprocess, "run")
    def test_rejects_crash_despite_success_marker(self, run):
        run.return_value = subprocess.CompletedProcess([], 1, "Nivo OS: boot OK\nDesktop: Willkommen", "crash")
        self.assertEqual(runner.main(), 1)
