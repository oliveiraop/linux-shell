import signal


class App:
    def __init__(self) -> None:
        self.loop = True

    def run(self):
        while self.loop:
            continue

    def stop_loop(self):
        self.loop = False
        print("Python proccess finalizing")


if __name__ == "__main__":
    app = App()
    signal_handler = signal.signal(signal.SIGTERM, app.stop_loop)
    app.run()
