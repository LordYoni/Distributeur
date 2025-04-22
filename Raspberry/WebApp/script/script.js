const socket = io();


Array.from(document.getElementsByClassName("card")).forEach(element => {

    element.addEventListener("click", e => {
        
        socket.emit("cardSelected", element.getAttribute("id") );
    })
});