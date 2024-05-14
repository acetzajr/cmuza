import sys
import time
from pyman.build import build as build_
from pyman.init import init as init_, check_in_options
from pyman.clean import clean as clean_
from pyman.run import run as run_

FORMAT = "{:,.3f}"


def format_time(t: float) -> str:
    return FORMAT.format(t)


def measure_fn(fn, *args, **kwargs) -> tuple[int, float]:
    start = time.time()
    code = fn(*args, **kwargs)
    elapsed = time.time() - start
    return [code, elapsed]


def need_some_arguments(n: int) -> bool:
    if len(sys.argv) <= n:
        print(f"> need at least {n} command line arguments")
        return True
    return False


def build() -> int:
    if need_some_arguments(2):
        return 1
    config = sys.argv[2]
    code = init_(config=config)
    if code != 0:
        return code
    return build_(config=config)


def run() -> int:
    if need_some_arguments(2):
        return 1
    config = sys.argv[2]
    code = init_(config=config)
    if code != 0:
        return code
    code = build_(config=config)
    if code != 0:
        return code
    return run_()


def init() -> int:
    if need_some_arguments(2):
        return 1
    config = sys.argv[2]
    return init_(config=config)


def rebuild() -> int:
    clean_()
    print("> build cleaned")
    if need_some_arguments(2):
        return 1
    config = sys.argv[2]
    code = init_(config=config)
    if code != 0:
        return code
    return build_(config=config)


def main():
    need_some_arguments(1)
    command = sys.argv[1]
    result = check_in_options(
        tag="command",
        options=["init", "build", "run", "clean", "rebuild"],
        value=command,
    )
    if result is None:
        return 1
    match command:
        case "build":
            return build()
        case "run":
            return run()
        case "init":
            return init()
        case "clean":
            clean_()
            print("> build cleaned")
            return 0
        case "rebuild":
            return rebuild()


if __name__ == "__main__":
    print(">> Muza")
    (code, total) = measure_fn(main)
    print(f"> total time: {format_time(total)} s")
    sys.exit(code)
