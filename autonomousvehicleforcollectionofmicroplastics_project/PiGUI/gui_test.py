from guizero import App, Text, TextBox, PushButton, Slider, Picture

def start_marvin():
    status_message.value="Started"
def stop_marvin():
    status_message.value="Stopped"
def change_speed():
    status_message.value="Speed changed"

app = App(title="M.A.R.V.I.N.", width=1280, height=720, layout="grid")

Text(app, text="M.A.R.V.I.N. Information Hub", size=34, font="Arial", color="blue", grid=[1,0,])
Picture(app, image="marvin.gif", grid=[0,1])
Picture(app, image="marvin.gif", grid=[1,1])
Picture(app, image="marvin.gif", grid=[2,1])
Picture(app, image="marvin.gif", grid=[3,1])
Picture(app, image="marvin.gif", grid=[4,1])
Picture(app, image="marvin.gif", grid=[5,1])

Text(app, text="Status: ", grid=[0,4])
status_message = Text(app, text="Stopped", grid=[1,4])

start_button = PushButton(app, command=start_marvin, text="START", grid=[0,2])
stop_button = PushButton(app, command=stop_marvin, text="STOP", grid=[1,2])
speed_slider = Slider(app, command=change_speed, start=1, end=10, grid=[0,5])










app.display()
