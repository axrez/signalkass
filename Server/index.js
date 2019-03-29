const express = require('express');
const bodyParser = require('body-parser');
const mongoose = require('mongoose');

const device = require("./routes/api/device");

const app = express();

// BodyParser middelware
app.use(bodyParser.urlencoded({ limit: '50mb' ,extended: true }))
app.use(bodyParser.json({ limit: '50mb', extended: true}))

// mongoose middelware
const db = require('./config/keys').mongoURI;
mongoose
  .connect(db, { useNewUrlParser: true })
  .then(() => console.log('Database connected'))
  .catch(err => console.log(err));

app.use("/api/device", device);

app.get("/", (req, res) => res.send("succes"));


const port = process.env.PORT || 3001
app.listen(port, () => console.log(`Server listening on port ${port}`));

