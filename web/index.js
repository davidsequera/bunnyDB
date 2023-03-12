
//Parse from String to HTML
function createTemplate(HTMLString) {
    const html = document.implementation.createHTMLDocument();
    // console.log(html)
    html.body.innerHTML = HTMLString;
    // console.log(HTMLString)
    return html.body.children[0];
}

//Samples or Templates

    function MovieTemplate(movie) {
        return(
            `<button onclick='openMask("${movie.id}")' class="movie" id=${movie.id}>
                <img src=${movie.img} alt=${movie.name}>
                <h2 class="movie-title">${movie.name}</h2>
            </button>`
        )
    }

    function SeatTemplate(seat) {
        return(
            `<li class="seat ${seat.type} ${seat.state}" id="${seat.id}">
                <h2>${seat.postion}</h2>
            </li>`
        )
    }

    function ShowtimeTemplate(showtime) {
        return(
            `<button onclick='showRoom("${showtime.id}")' class="showtime" id=${showtime.id}>
                <p>${showtime.time}</p>
            </button>`
        )
    }
    

//Pinters

    function printMovies(array, place){
        array.map(element => {
            const htmlstring = MovieTemplate(element)
            // console.log(htmlstring)
            const peopleElement = createTemplate(htmlstring);
            // console.log(peopleElement)
            place.append(peopleElement)
        })
    }
    function printSeats(array, showtime_id){
        const {general, preferential} = {general:document.getElementById("general"), preferential: document.getElementById("preferential")}
        // if(general)
        const copy = array.filter(e => e.showtime_id === showtime_id)
        array = copy.filter(e => e.type === 'G')
        array.map(element => {
            const htmlstring = SeatTemplate(element)
            const peopleElement = createTemplate(htmlstring)
            general.append(peopleElement)
        })
        array = copy.filter(e => e.type === 'P')
        array.map(element => {
            const htmlstring = SeatTemplate(element)
            const peopleElement = createTemplate(htmlstring)
            preferential.append(peopleElement)
        })
    }
    function printShowtimes(array, movie_id){
        const place = document.getElementById('showtimes')
        array = array.filter(e => e.movie_id === movie_id)
        array.map(element => {
            const htmlstring = ShowtimeTemplate(element)
            // console.log(htmlstring)
            const peopleElement = createTemplate(htmlstring);
            // console.log(peopleElement)
            place.append(peopleElement)
        })
    }

const carousel = document.getElementById('carousel')

printMovies(db.MOVIE, carousel)


//Here is the onClick Code
function openMask(movie_id){
    const closeElement = document.getElementById("mask")
    closeElement.classList.remove("hidden")
    cleanAllChild('showtimes')
    printShowtimes(db.SHOWTIME, movie_id)
    const array = db.SHOWTIME.filter(e => e.movie_id === movie_id)
    printSeats(db.SEAT, array[0].id)
    selected(array[0].id)

    const [room] = db.ROOM.filter(e => e.id === array[0].room_id)

    const roomTitle = document.getElementById('room-title')
    roomTitle.textContent = room.name
}
function closeMask(){
    const closeElement = document.getElementById("mask")
    closeElement.classList.add("hidden")
    cleanAllChild('showtimes')
    cleanAllChild('general')
    cleanAllChild('preferential')
}


function showRoom(showtime_id){
    cleanAllChild('general')
    cleanAllChild('preferential')


    const [showtime] = db.SHOWTIME.filter(e => e.id === showtime_id)
    const [room] = db.ROOM.filter(e => e.id === showtime.room_id)
    
    const roomTitle = document.getElementById('room-title')
    roomTitle.textContent = room.name

    selected(showtime_id)
    printSeats(db.SEAT, showtime_id)
}


//Others Functions

function selected(showtime_id){
    const [showtime] = db.SHOWTIME.filter(e => e.id === showtime_id)
    const Others = db.SHOWTIME.filter(e => e.movie_id === showtime.movie_id)
    Others.forEach(e => {
        let a = document.getElementById(e.id)
        a.classList.remove("selected")
    });
    a = document.getElementById(showtime.id)
    a.classList.add("selected")
}

function cleanAllChild(a){
    const myNode = document.getElementById(a);
    myNode.textContent = '';
}

