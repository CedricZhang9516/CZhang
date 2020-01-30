
      status = m_tuple0->addItem ("run",  m_run );
      status = m_tuple0->addItem ("rec",  m_rec );

      status = m_tuple0->addItem("indexmc",          m_idxmc, 0, 100);
      status = m_tuple0->addIndexedItem("trkidx",    m_idxmc, m_trkidx);
      status = m_tuple0->addIndexedItem("pdgid",     m_idxmc, m_pdgid);
      status = m_tuple0->addIndexedItem("motheridx", m_idxmc, m_motheridx);

  SmartDataPtr<Event::EventHeader> eventHeader(eventSvc(),"/Event/EventHeader");
  m_run = eventHeader->runNumber();
  m_rec = eventHeader->eventNumber();

  //MC information
  if (eventHeader->runNumber()<0)
  {

    SmartDataPtr<Event::McParticleCol> mcParticleCol(eventSvc(), "/Event/MC/McParticleCol");

    int m_numParticle = 0;
    if (!mcParticleCol)
    {
      std::cout << "Could not retrieve McParticelCol" << std::endl;
      return StatusCode::FAILURE;
    }
    else
    {
      bool psipDecay = false;
      int rootIndex = -1;
      Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
      for (; iter_mc != mcParticleCol->end(); iter_mc++)
      {
        if ((*iter_mc)->primaryParticle()) continue;
        if (!(*iter_mc)->decayFromGenerator()) continue;
        //if ( ((*iter_mc)->mother()).trackIndex()<3 ) continue;
        if ((*iter_mc)->particleProperty()==100443) 
        {
          psipDecay = true;
          rootIndex = (*iter_mc)->trackIndex();
        }
        if (!psipDecay) continue;
        int trkidx = (*iter_mc)->trackIndex() - rootIndex;
        int pdgid = (*iter_mc)->particleProperty();
        int mcidx = ((*iter_mc)->mother()).trackIndex() - rootIndex;
        m_trkidx[m_numParticle] = trkidx;
        m_pdgid[m_numParticle] = pdgid;
        m_motheridx[m_numParticle] = mcidx;
        m_numParticle += 1;    
      }
    }
    m_idxmc = m_numParticle;
  }
