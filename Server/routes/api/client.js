const express = require('express')
const router = express.Router()

const Measure = require('../../models/Measurement')

router.get('/', (req,res) => {
  Measure.find().limit(1).sort({$natural: -1})
    .then(m => res.json(m))
    .catch(err => console.log(err))
})

