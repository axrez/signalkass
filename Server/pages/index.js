import React from 'react'
import styled from 'styled-components'

import Graph from '../components/Graph'

const GraphWrapper = styled.div`
  max-width: 80vw;
  height: 30vh;
`

const Index = () => (
  <>
    <h1>Hello</h1>
    <GraphWrapper>
      <Graph />
    </GraphWrapper>
  </>
)

export default Index

