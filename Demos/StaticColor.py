"""
@project : pyrgbdev
@author : Gooday2die
@date : 2022-02-13
@file : StaticColor.py
"""

import threading
import requests


from abstractDemo import AbstractDemo


class Demo(AbstractDemo):
    def __init__(self):
        """
        An initializer method for class Demo in RainbowAll
        """
        self.thread = None
        self.is_running = False
        self.r = 0
        self.g = 0
        self.b = 0

    def run(self, **kwargs):
        """
        An abstract method for running this demo.
        This method will have main features of the demo script.
        :return: returns None
        """
        self.thread = threading.Thread(target=self.__static_color)
        self.r = kwargs['r']
        self.g = kwargs['g']
        self.b = kwargs['b']
        self.url = kwargs['url']
        self.is_running = True
        self.thread.start()

    def stop(self):
        """
        An abstract method for stopping this demo.
        This method will terminate the demo script and this object.
        :return:
        """
        self.is_running = False
        self.thread.join()

    def __static_color(self):
        """
        A function that sets a single color over all devices
        :return: returns None
        """
        while self.is_running:
            requests.post(self.url + "/all/set_rgb/", json={"DeviceType": "All", "r": self.r,
                                                            "g": self.g, "b": self.b})
        return


if __name__ == '__main__':
    static_color = Demo()
    static_color.run(url="http://127.0.0.1:9000", r=255, g=255, b=255)
