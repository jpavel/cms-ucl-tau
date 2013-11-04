#ifndef RunLumiEvent_H
#define RunLumiEvent_H

class RunLumiEvent
{
	public: 
    RunLumiEvent(long run, long lumi, long event)
    {
      this->run = run;
      this->lumi = lumi;
      this->event = event;
    }
    long run;
    long lumi;
    long event;
    
    bool operator<(const RunLumiEvent& rle) const
    {
      if(this->run == rle.run)
      {
		if(this->lumi==rle.lumi)
		{
			return this->event < rle.event;
		}else{
			return this->lumi < rle.lumi;
		}
	  }else{
		return this->run < rle.run;
	  }
    }
    
    bool operator==(const RunLumiEvent& rle) const
    {
      bool equal = false;
      if(this->run == rle.run)
      {
		if(this->lumi == rle.lumi)
		{ 
			if (this->event == rle.event)
				equal=true;
		}
	  }
      return equal;
	  
    }

};

#endif // RunLumiEvent_H
