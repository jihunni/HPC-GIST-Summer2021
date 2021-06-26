---
layout: home
title: HPC-GIST-Summer2021
nav_exclude: true
seo:
  type: Course
  name: High-Performance Computing
---

# {{ site.tagline }}
{: .mb-2 }
{{ site.description }}
{: .fs-6 .fw-300 }

{% assign instructors = site.staffers | where: 'role', 'Instructor' %}
{% for staffer in instructors %}
{{ staffer }}
{% endfor %}

{% assign overview = site.slides | where: "title", "Overview" | first %}
{{ overview.content }}

[Join Lecture via Zoom](https://slu.zoom.us/j/95870673825)

{% for module in site.modules %}
{{ module }}
{% endfor %}

