import tkinter
import requests

from tkinter import simpledialog
from tkinter import DISABLED
from tkinter.font import BOLD
from tkinter import messagebox

import RainbowAll
import ScreenReactive
import StaticColor


class InitUI:
    def __init__(self):
        self.root = tkinter.Tk()
        self.root.withdraw()
        self.url = ""

    def ask_url(self):
        url = simpledialog.askstring(title="RGBonREST Demo",
                                     prompt="Enter URL:",
                                     initialvalue="http://127.0.0.1:9000")
        self.url = url

    def check_connection(self):
        try:
            result = requests.get(self.url + "/general/connection/")
            if result.status_code == 200:
                return True
            else:
                return False
        except:  # Yes, I know that using bare exception is bad. Too many things can go wrong here.
            return False

    def failed_connection(self):
        messagebox.showerror("Connection Failure", "Could not connect " + self.url)

    def get_url(self):
        return self.url


class MainUI:
    """
    A class for main ui of this program
    """
    def __init__(self, arg_url):
        """
        An initializer method for class UI
        """
        self.master = tkinter.Tk()
        self.master.title("pyrgbdev Demo GUI")
        self.master.geometry("450x300")
        self.master.resizable(width=False, height=False)

        self.cur_mode_text = tkinter.StringVar()  # For current mode that is located in mid up screen
        self.cur_mode = None

        self.error_text = tkinter.StringVar()
        self.error = ""

        self.button1 = None  # For Screen Reactive
        self.button2 = None  # For Rainbow All
        self.button3 = None  # For Static Colors
        self.button4 = None  # For Exit

        self.r_val = None  # For Red value of Static Colors
        self.g_val = None  # For Green value of Static Colors
        self.b_val = None  # For Blue value of Static Colors
        self.delay_val = None  # For delay value of rainbow all

        self.connected_devices = None  # For all connected devices
        self.url = arg_url
        self.demo_object = None

    def start(self):
        """
        A method for setting all attributes into places and starting the object
        :return: returns None
        """
        self.set_buttons()
        self.set_labels()
        self.set_inputs()
        self.show_connected_devices()
        self.master.mainloop()

    def set_buttons(self):
        """
        A method that sets all buttons in place
        :return: returns None
        """
        self.button1 = tkinter.Button(self.master, text="Screen Reactive", command=self.screen_reactive)
        self.button1.place(x=10, y=30, width=200, height=50)

        self.button2 = tkinter.Button(self.master, text="Rainbow All", command=self.rainbow_all)
        self.button2.place(x=10, y=90, width=200, height=50)

        self.button3 = tkinter.Button(self.master, text="Static Color", command=self.static)
        self.button3.place(x=10, y=175, width=200, height=50)

        self.button4 = tkinter.Button(self.master, text="EXIT", command=self.exit_program)
        self.button4.place(x=240, y=225, width=200, height=30)

    def exit_program(self):
        """
        A method that exits the program
        :return: returns None, Exits with 0
        """
        self.master.destroy()
        try:
            self.demo_object.stop()
        except AttributeError:  # When demo object was not connected.
            pass  # just pass
        del self.demo_object
        result = requests.delete(self.url + "/all/disconnect")

    def set_labels(self):
        """
        A method that sets labels in the ui section
        :return: returns None
        """
        tkinter.Label(self.master, text="R").place(x=10, y=235)
        tkinter.Label(self.master, text="G").place(x=65, y=235)
        tkinter.Label(self.master, text="B").place(x=120, y=235)

        tkinter.Label(self.master, text="Delay : ").place(x=10, y=150)

        tkinter.Label(self.master, text="Current Mode : ", font=('arial', 9, BOLD)).place(x=10, y=5)
        tkinter.Label(self.master, text="Connected Devices", font=('arial', 9, BOLD)).place(x=275, y=5)

        self.cur_mode = tkinter.Label(self.master, textvariable=self.cur_mode_text)
        self.cur_mode.place(x=100, y=5)

        self.error = tkinter.Label(self.master, textvariable=self.error_text)
        self.error.place(x=10, y=265)

    def set_inputs(self):
        """
        A method that sets input fields for values in the ui field
        :return: returns None
        """
        self.r_val = tkinter.Entry(self.master)
        self.g_val = tkinter.Entry(self.master)
        self.b_val = tkinter.Entry(self.master)
        self.delay_val = tkinter.Entry(self.master)

        self.r_val.insert(tkinter.INSERT, "255")  # set example values for inputs
        self.g_val.insert(tkinter.INSERT, "255")
        self.b_val.insert(tkinter.INSERT, "255")
        self.delay_val.insert(tkinter.INSERT, "0.0001")

        self.r_val.place(x=30, y=235, width=30)
        self.g_val.place(x=85, y=235, width=30)
        self.b_val.place(x=140, y=235, width=30)

        self.delay_val.place(x=60, y=150, width=75)

    def show_connected_devices(self):
        """
        A method that shows the connected devices in right text area
        :return: returns None
        """
        self.connected_devices = tkinter.Text(self.master)
        self.connected_devices.place(x=240, y=30, width=200, height=175)

        dev_list = requests.get(self.url + "/all/get_devices").json()
        print(dev_list)
        connected_device_string = ""
        try:
            for sdk in dev_list:
                connected_device_string = connected_device_string + "- " + str(sdk) + "\n"
                for device_type in dev_list[sdk]:
                    for device in dev_list[sdk][device_type]:
                        connected_device_string = connected_device_string + str(device_type) + " : " + \
                                          str(device[0]) + "\n"
        except TypeError:
            connected_device_string = "No Connected Devices"

        self.connected_devices.insert(tkinter.INSERT, connected_device_string)
        self.connected_devices.config(state=DISABLED)

    def screen_reactive(self):
        """
        A method that runs screen reactive using multi thread
        :return: returns None
        """
        self.cur_mode_text.set("Screen Reactive")
        self.demo_object = ScreenReactive.Demo()
        self.demo_object.run(url=self.url)

    def rainbow_all(self):
        """
        A method that runs Rainbow all using multi thread
        :return: returns None
        """
        try:
            delay = float(self.delay_val.get())
            if not 0 <= delay <= 10:
                raise ValueError

            self.cur_mode_text.set("Rainbow All - Delay : " + self.delay_val.get())

            try:  # If there were any process that was running RGB control, terminate it
                self.demo_object.stop()
                del self.demo_object
            except AttributeError:  # If this was the first control, pass
                pass
            self.demo_object = RainbowAll.Demo()
            self.demo_object.run(url=self.url, delay=delay)

        except ValueError:
            self.error_text.set("Error : Delay Value must be Float (0 ~ 10)")

    def static(self):
        """
        A method that runs static rainbow effect with multi thread
        :return: returns None
        """
        try:  # check if the rgb value is valid
            rgb_val = (int(self.r_val.get()), int(self.g_val.get()), int(self.b_val.get()))
            for color_val in rgb_val:  # check value range
                if not 0 <= color_val <= 255:
                    raise ValueError
            self.cur_mode_text.set("Static Color - " + str(rgb_val))

            try:  # If there were any process that was running RGB control, terminate it
                self.demo_object.stop()
                del self.demo_object
            except AttributeError:  # If this was the first control, pass
                pass
            self.demo_object = StaticColor.Demo()
            self.demo_object.run(url=self.url, r=rgb_val[0], g=rgb_val[1], b=rgb_val[2])

        except ValueError:
            self.error_text.set("Error : RGB Values must be Integers (0 ~ 255)")


def init_stage():
    init_ui = InitUI()
    init_ui.ask_url()
    connection_result = init_ui.check_connection()

    if connection_result:
        return init_ui.get_url()
    else:
        init_ui.failed_connection()
        exit(-1)


if __name__ == "__main__":
    print("Starting UI")
    url = init_stage()
    print("Using url: " + url)
    gui = MainUI(url)
    gui.start()
    print("Stopped UI")
    exit(0)
