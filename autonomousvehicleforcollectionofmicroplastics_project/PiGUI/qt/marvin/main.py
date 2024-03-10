# always seem to need this
import sys, os

# This gets the Qt stuff
import PyQt5
from PyQt5.QtWidgets import *

# This is our window from QtCreator
import mainwindow_auto

# create class for our Raspberry Pi GUI
class MainWindow(QMainWindow, mainwindow_auto.Ui_MainWindow):
 # access variables inside of the UI's file

 ### functions for the buttons to call
  def pressedOnButton(self):
    lblStatus.text="STARTED"
  def pressedOffButton(self):
    lblStatus.text="STOPPED"
  def pressedModeButton(self):
    if btnMode.text == "AUTO":
      btnMode.text = "MANUAL" else btnMode.text = "AUTO"
  def pressedModeButton(self):
    os.system('sudo reboot now')

 def __init__(self):
 super(self.__class__, self).__init__()
 self.setupUi(self) # gets defined in the UI file

 ### Hooks to for buttons
  self.btnOn.clicked.connect(lambda: self.pressedOnButton())
  self.btnOff.clicked.connect(lambda: self.pressedOffButton())
  self.btnMode.clicked.connect(lambda: self.pressedModeButton())
  self.btnReboot.clicked.connect(lambda: self.pressedRebootButton())

# I feel better having one of these
def main():
 # a new app instance
 app = QApplication(sys.argv)
 form = MainWindow()
 form.show()
 # without this, the script exits immediately.
 sys.exit(app.exec_())

# python bit to figure how who started This
if __name__ == "__main__":
 main()
